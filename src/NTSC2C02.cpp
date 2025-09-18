#include <iostream>
#include "NTSC2C02.h"
#include "NESIncludes.h"


uint16_t calcLocation(uint16_t x, uint16_t y, uint16_t rowSize) {
  return (y * rowSize) + x;
}

void Tile::loadTile(uint16_t tileNum, std::array<uint8_t, 0x1000>& patternTable0, std::array<uint8_t, 0x1000>& patternTable1) {
  uint16_t tileAddress = tileNum * 0x10;
  std::array<uint8_t, 0x1000>& patternTable = patternTable0;
  if (tileNum > 0xFF) {
    patternTable = patternTable1;
    tileAddress = (tileNum - 0x100) * 0x10;
  }
  for (uint16_t j = 0; j < 0x08; j++) {
    for (uint16_t i = 0; i < 0x08; i++) {
      uint8_t p0 = (patternTable[tileAddress + j] >> (0x07 - i)) & 0x01;
      uint8_t p1 = (patternTable[tileAddress + 0x08 + j] >> (0x07 - i)) & 0x01;
      tileData[calcLocation(i, j, 0x08)] = (p1 << 1) | p0;
    }
  }
}

Color Tile::getColor(uint16_t pixel, Color * palette) {
  return palette[currentPalette[tileData[pixel]]];
}


void Register::set(uint8_t val) {
  reg = val;
}

void Register::setFlags(uint8_t byte, bool val) {
  if (val) {
    reg |= val ? byte : 0x0;
  } else {
    reg &= ~(val ? byte : 0x0);
  }
}

void Register::setFlags(uint8_t byte) {
  setFlags(byte, 0x1);
}

uint8_t Register::get() {
  return reg;
}

uint8_t Register::getFlag(uint8_t bit) {
  return (reg & bit) ? 0x1 : 0x0;
}


NTSC2C02::NTSC2C02(Memory * mem) : memory(mem) {
    mapMemoryToTables();
    //mapMemoryToCPUBus(mem);
};

Tile NTSC2C02::generateTile(uint32_t tileNum) {
  Tile tile = Tile();
  tile.loadTile(tileNum, patternTable0, patternTable1);
  return tile;
}

void NTSC2C02::incVertV() {
  // https://www.nesdev.org/wiki/PPU_scrolling#Y_increment
  if ((v & 0x7000) != 0x7000) {       // if fine Y < 7
    v += 0x1000;                      // increment fine Y
  } else {
    v &= ~0x7000;                     // fine Y = 0
    uint16_t y = (v & 0x03E0) >> 5;        // let y = coarse Y
    if (y == 29) {
      y = 0;                          // coarse Y = 0
      v ^= 0x0800;                    // switch vertical nametable
    } else if (y == 31) {
      y = 0;                          // coarse Y = 0, nametable not switched
    } else {
      y += 1;
    }                         // increment coarse Y
    v = (v & ~0x03E0) | (y << 5);     // put coarse Y back into v
  }
}

void NTSC2C02::incHoriV() {
  // https://www.nesdev.org/wiki/PPU_scrolling#Coarse_X_increment
  if ((v & 0x001F) == 31) {// if coarse X == 31
    v &= ~0x001F;          // coarse X = 0
    v ^= 0x0400;           // switch horizontal nametable
  } else {
    v += 1;                // increment coarse X
  }
}

void NTSC2C02::mapMemoryToTables() {
  PPUAddressMappingFunction* ppuAddressMappingFunction = new PPUAddressMappingFunction(this);
  memory->mapAddressRange(0x0000, 0x2FFF, ppuAddressMappingFunction);
}
void NTSC2C02::mapMemoryToCPUBus(Memory * mem) {
  CPUToPPUAddressMappingFunction* cpuToPPUMappingFunction = new CPUToPPUAddressMappingFunction(this);
  mem->mapAddressRange(0x2000, 0x2007, cpuToPPUMappingFunction);
}

void NTSC2C02::tick(R6502 * cpu) {
  if (scanLineCycle == 256) {
    incVertV();
    //incHoriV();
  }
  
  if (scanLineCycle == 257) {
    // Reset horizontal position
    v = (v & 0x7BE0) | (t & 0x041F);
  }


  if (scanLine == 261) {
    if (scanLineCycle == 0) {
      frame = (frame + 1) % 2;
      frameComplete = 0x1;
      allowMaskWrites = 0x1;
    } else if (scanLineCycle == 1) {
      frameComplete = 0x0;
      PPUSTATUS->setFlags(STATUS_V, 0x0);
      vBlankStatusNotRead = 0x01;
    }
    if (scanLineCycle >= 257 && scanLineCycle <= 320) {
      OAMADDR->set(0x00);
      // Sprite evaluation
    }
    if (scanLineCycle >= 280 && scanLineCycle <= 304) {
      // Reset vertical position
      v = (v & 0x041F) | (t & 0x7BE0);
    }
    bool renderingEnabled = (PPUMASK->getFlag(MASK_b) || PPUMASK->getFlag(MASK_s));
    if (scanLineCycle == 339 && frame == 0 && renderingEnabled) {
      scanLineCycle = 340;
    }
  } else if (scanLine <= 239) {
    if (scanLineCycle == 0) {
      // Do nothing
    } else if (scanLineCycle <= 256) {
      uint16_t scanLinePhaseCycle = scanLineCycle - 1;
      // https://www.nesdev.org/wiki/PPU_scrolling#Tile_and_attribute_fetching
      uint16_t tileAddress = 0x2000 | (v & 0x0FFF);
      uint16_t attributeAddress = 0x23C0 | (v & 0x0C00) | ((v >> 4) & 0x38) | ((v >> 2) & 0x07);
      switch (scanLineCycle % 8) {
        case 1:
          // Fetch name table byte
          nameTableByte = memory->read(tileAddress);
          break;
        case 3:
          // Fetch attribute table byte
          attributeTableByte = memory->read(attributeAddress);
          break;
        case 5:
          // Fetch low pattern table tile byte
          tmpLowPatternTableTileByte = memory->read(((PPUCTRL->getFlag(CTRL_B) ? 0x1000 : 0x0000) | (nameTableByte << 4) | ((v >> 12) & 0x07)));
          break;
        case 7:
          // Fetch high pattern table tile byte
          tmpHighPatternTableTileByte = memory->read(((PPUCTRL->getFlag(CTRL_B) ? 0x1000 : 0x0000) | (nameTableByte << 4) | 0x0008 | ((v >> 12) & 0x07)));
          break;
        case 0:
          lowPatternTableTileByte = tmpLowPatternTableTileByte;
          highPatternTableTileByte = tmpHighPatternTableTileByte;
          incHoriV();
          break;
        default:
          break;
      }

      uint8_t shiftAmount = 7 - ((scanLinePhaseCycle) % 8);
      uint8_t p0 = (lowPatternTableTileByte >> shiftAmount) & 0x01;
      uint8_t p1 = (highPatternTableTileByte >> shiftAmount) & 0x01;
      //uint8_t paletteIndex = (p1 << 1) | p0;
      //Color bgColor = palette[paletteIndex];

      // Select quadrant inside the 4x4 tile block
      uint16_t coarseX =  (v & 0x001F);
      uint16_t coarseY = ((v & 0x03E0) >> 5);
      uint8_t quadrant = ((coarseY & 0x02) ? 0x02 : 0x00) | ((coarseX & 0x02) ? 0x01 : 0x00);

      // Shift attribute byte to get the 2 high bits for this quadrant
      uint8_t attrHigh = (attributeTableByte >> (quadrant * 2)) & 0x03;

      // Final palette index = attrHigh (bits 2-3) | pattern bits (bits 0-1)
      uint8_t paletteIndex = (attrHigh << 2) | ((p1 << 1) | p0);

      // Then map paletteIndex through your palette RAM (normally $3F00..)
      Color bgColor = palette[paletteIndex];
      pixMap[calcLocation(scanLinePhaseCycle, scanLine, 0x100)] = bgColor;

    } else if (scanLineCycle <= 320) {
      // Fetch sprite data
      /*uint16_t scanLinePhaseCycle = scanLineCycle - 257;
      // Fetch tile data
      switch (scanLineCycle % 8) {
        case 1:
          // Fetch garbage name table byte
          //nameTableByte = memory->read(tileAddress);
          break;
        case 3:
          // Fetch garbage name table byte
          //nameTableByte = memory->read(tileAddress);
          break;
        case 5:
          // Fetch low pattern table tile byte
          //tmpLowPatternTableTileByte = memory->read(((PPUCTRL->getFlag(CTRL_B) ? 0x1000 : 0x0000) | (nameTableByte << 4) | ((v >> 12) & 0x07)));
          break;
        case 7:
          // Fetch high pattern table tile byte
          //tmpHighPatternTableTileByte = memory->read(((PPUCTRL->getFlag(CTRL_B) ? 0x1000 : 0x0000) | (nameTableByte << 4) | 0x0008 | ((v >> 12) & 0x07)));
          break;
        default:
          break;
      }
          */
    } else if (scanLineCycle <= 336) {
      uint16_t scanLinePhaseCycle = scanLineCycle - 321;
      if (scanLineCycle % 8 == 0) {
        incHoriV();
      }
      // Idle
    } else if (scanLineCycle <= 340) {
      /*uint16_t scanLinePhaseCycle = scanLineCycle - 337;
      if ((scanLineCycle) % 4 == 0) {
        // Fetch tile data
        switch ((scanLineCycle / 4) % 2) {
          case 0:
            // Fetch name table byte (unknown reason)
            //nameTableByte = memory->read(tileAddress);
            break;
          case 1:
            // Fetch name table byte (unknown reason)
            //nameTableByte = memory->read(tileAddress);
            break;
          default:
            break;
        }
      } else {
        // Do nothing
      }*/
    }
  } else if (scanLine == 240) {
    // Post render scanline
  } else if (scanLine <= 260) {
    if (scanLine == 241)
      //std::cout << "VBLANK Scanline: " << scanLine << " Cycle: " << scanLineCycle << std::endl;
    if (scanLine == 241 && scanLineCycle == 1) {
      //std::cout << "VBLANK\n" << std::endl;
      //std::cout << "ppu 2002: " << std::hex << int(PPUSTATUS->get()) << std::dec << std::endl;
      //std::cout << "cpu 2002: " << std::hex << int(cpu->memory->read(0x2002)) << std::dec << std::endl;
      PPUSTATUS->setFlags(STATUS_V, 0x1);
      if (PPUCTRL->getFlag(CTRL_V) && vBlankStatusNotRead) {
        cpu->nmiPending = 0x01;
        vBlankStatusNotRead = 0x00;
      }
    }
  }

  if (scanLineCycle < 340) scanLineCycle++;
  else scanLineCycle = 0;
  if (scanLineCycle == 0) {
    //std::cout << "Scanline: " << scanLine << std::endl;
    if (scanLine < 261) scanLine++;
    else scanLine = 0;
  }
}


CPUToPPUAddressMappingFunction::CPUToPPUAddressMappingFunction(NTSC2C02 * ppu) : ppu(ppu), AddressMappingFunction(ppu->memory->ram) {}
uint8_t CPUToPPUAddressMappingFunction::read(uint16_t addr) {
    switch (addr) {
      case 0x2000:
          return ppu->PPUCTRL->get();
      case 0x2001:
          return ppu->PPUMASK->get();
      case 0x2002: {
          uint8_t tmp = ppu->PPUSTATUS->get();
          ppu->PPUSTATUS->setFlags(ppu->STATUS_V, 0x0); // Clear VBlank flag
          ppu->w = 0x00;
          return tmp;
      }
      case 0x2003:
          return ppu->OAMADDR->get();
      case 0x2004:
          if (ppu->PPUMASK->getFlag(ppu->MASK_s) || ppu->PPUMASK->getFlag(ppu->MASK_b)) {
            // rendering is enabled, return open bus
            return 0x00;
          }
          return ppu->OAMDATA->get();
      case 0x2005:
          return ppu->PPUSCROLL->get();
      case 0x2006:
          return ppu->PPUADDR->get();
      case 0x2007:
          if (ppu->PPUMASK->getFlag(ppu->MASK_s) || ppu->PPUMASK->getFlag(ppu->MASK_b)) {
            // rendering is enabled, return open bus
            return 0x00;
          }
          if (ppu->PPUCTRL->getFlag(ppu->CTRL_I)) {
            ppu->PPUADDR->set(ppu->PPUADDR->get() + 32); // Increment by 32
          } else {
            ppu->PPUADDR->set(ppu->PPUADDR->get() + 1); // Increment by 1
          }
          return ppu->PPUDATA->get();
      default:
          return 0x00;
    }
}
void CPUToPPUAddressMappingFunction::write(uint16_t addr, uint8_t data) {
    std::cout << "PPU Write to " << std::hex << addr << " data: " << (int)data << std::dec << std::endl;
    switch (addr) {
      case 0x2000:
          ppu->PPUCTRL->set(data);
          ppu->t = (((uint16_t) data & 0x03) << 10) | (ppu->t & 0xF3FF);
          break;
      case 0x2001:
          if (ppu->allowMaskWrites) ppu->PPUMASK->set(data);
          break;
      case 0x2002:
          // status register is read only
          break;
      case 0x2003:
          ppu->OAMADDR->set(data);
          break;
      case 0x2004:
          if (ppu->PPUMASK->getFlag(ppu->MASK_s) || ppu->PPUMASK->getFlag(ppu->MASK_b)) {
            // rendering is enabled, do nothing
            break;
          }
          ppu->OAMDATA->set(data);
          ppu->OAM[ppu->OAMADDR->get()] = data;
          ppu->OAMADDR->set(ppu->OAMADDR->get() + 1); // Increment OAMADDR
          break;
      case 0x2005:
          ppu->PPUSCROLL->set(data);
          if (ppu->w == 0) {
            ppu->t = ((uint16_t) data >> 3) | (ppu->t & 0xFFE0);
            ppu->x = data & 0x07;
            ppu->w = 1;
          } else {
            ppu->t = ((((uint16_t) data) & 0x07) << 12) |
                     ((((uint16_t) data) & 0xF8) << 2) |
                      (ppu->t & 0x0C1F);

            ppu->w = 0;
          }
          break;
      case 0x2006:
          if (ppu->w == 0) {
            ppu->t = ((uint16_t)(data & 0x3F) << 8) | (ppu->t & 0x00FF);
            ppu->w = 1;
          } else {
            ppu->t = (((uint16_t) data) | (ppu->t & 0x7F00));
            ppu->v = ppu->t;
            ppu->w = 0;
          }
          ppu->PPUADDR->set(data);
          break;
      case 0x2007:
          if (ppu->PPUMASK->getFlag(ppu->MASK_s) || ppu->PPUMASK->getFlag(ppu->MASK_b)) {
            // rendering is enabled, do nothing
            break;
          }
          ppu->memory->write(ppu->PPUADDR->get(), data);
          std::cout << "Wrote " << std::hex << (int)data << " to " << std::hex << ppu->PPUADDR->get() << std::dec << std::endl;
          if (ppu->PPUCTRL->getFlag(ppu->CTRL_I)) {
            ppu->PPUADDR->set(ppu->PPUADDR->get() + 32); // Increment by 32
          } else {
            ppu->PPUADDR->set(ppu->PPUADDR->get() + 1); // Increment by 1
          }
          ppu->PPUDATA->set(data);
          break;
      default:
          break;
    }
}


PPUAddressMappingFunction::PPUAddressMappingFunction(NTSC2C02 * ppu) : ppu(ppu), AddressMappingFunction(ppu->memory->ram) {}
uint8_t PPUAddressMappingFunction::read(uint16_t addr) {
  if (addr >= 0x0000 && addr <= 0x0FFF) {
      return ppu->patternTable0[addr];
  } else if (addr >= 0x1000 && addr <= 0x1FFF) {
      return ppu->patternTable1[addr - 0x1000];
  } else if (addr >= 0x2000 && addr <= 0x23BF) {
      return ppu->nameTable0[addr - 0x2000];
  } else if (addr >= 0x23C0 && addr <= 0x23FF) {
      return ppu->attributeTable0[addr - 0x23C0];
  } else if (addr >= 0x2400 && addr <= 0x27BF) {
      return ppu->nameTable1[addr - 0x2400];
  } else if (addr >= 0x27C0 && addr <= 0x27FF) {
      return ppu->attributeTable1[addr - 0x27C0];
  } else if (addr >= 0x2800 && addr <= 0x2BBF) {
      return ppu->nameTable0[addr - 0x2800]; // Mirror
  } else if (addr >= 0x2BC0 && addr <= 0x2BFF) {
      return ppu->attributeTable2[addr - 0x2BC0];
  } else if (addr >= 0x2C00 && addr <= 0x2FBF) {
      return ppu->nameTable1[addr - 0x2C00]; // Mirror
  } else if (addr >= 0x2FC0 && addr <= 0x2FFF) {
      return ppu->attributeTable3[addr - 0x2FC0];
  } else if (addr >= 0x3000 && addr <= 0x3EFF) {
      // Mirrors of 2000-2EFF
      return read(addr - 0x1000);
  } else if (addr >= 0x3F00 && addr <= 0x3F1F) {
      return ppu->paletteRam[addr - 0x3F00];
  } else if (addr >= 0x3F20 && addr <= 0x3FFF) {
      // Mirrors of 3F00-3F1F
      return read(0x3F00 + (addr % 0x20));
  }
  return 0x00;
}
void PPUAddressMappingFunction::write(uint16_t addr, uint8_t data) {
  if (addr >= 0x0000 && addr <= 0x0FFF) {
      ppu->patternTable0[addr] = data;
  } else if (addr >= 0x1000 && addr <= 0x1FFF) {
      ppu->patternTable1[addr - 0x1000] = data;
  } else if (addr >= 0x2000 && addr <= 0x23BF) {
      ppu->nameTable0[addr - 0x2000] = data;
  } else if (addr >= 0x23C0 && addr <= 0x23FF) {
      ppu->attributeTable0[addr - 0x23C0] = data;
  } else if (addr >= 0x2400 && addr <= 0x27BF) {
      ppu->nameTable1[addr - 0x2400] = data;
  } else if (addr >= 0x27C0 && addr <= 0x27FF) {
      ppu->attributeTable1[addr - 0x27C0] = data;
  } else if (addr >= 0x2800 && addr <= 0x2BBF) {
      ppu->nameTable0[addr - 0x2800] = data; // Mirror
  } else if (addr >= 0x2BC0 && addr <= 0x2BFF) {
      ppu->attributeTable2[addr - 0x2BC0] = data;
  } else if (addr >= 0x2C00 && addr <= 0x2FBF) {
      ppu->nameTable1[addr - 0x2C00] = data; // Mirror
  } else if (addr >= 0x2FC0 && addr <= 0x2FFF) {
      ppu->attributeTable3[addr - 0x2FC0] = data;
  } else if (addr >= 0x3000 && addr <= 0x3EFF) {
      // Mirrors of 2000-2EFF
      write(addr - 0x1000, data);
  } else if (addr >= 0x3F00 && addr <= 0x3F1F) {
      ppu->paletteRam[addr - 0x3F00] = data;
  } else if (addr >= 0x3F20 && addr <= 0x3FFF) {
      // Mirrors of 3F00-3F1F
      write(0x3F00 + (addr % 0x20), data);
  }
}