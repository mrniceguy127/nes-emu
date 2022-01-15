BEGIN {
  FS=","
  print "{"
}

NR!=1 {
  ADDR_MODE="XXX"
  if ($2=="relative") {
    ADDR_MODE="REL"
  } else if ($2=="abs") {
    ADDR_MODE="ABS"
  } else if ($2=="absx") {
    ADDR_MODE="ABX"
  } else if ($2=="absy") {
    ADDR_MODE="ABY"
  } else if ($2=="indirect") {
    ADDR_MODE="IND"
  } else if ($2=="indx") {
    ADDR_MODE="IZX"
  } else if ($2=="indy") {
    ADDR_MODE="IZY"
  } else if ($2=="imm") {
    ADDR_MODE="IMM"
  } else if ($2=="implied") {
    ADDR_MODE="IMP"
  } else if ($2=="zp") {
    ADDR_MODE="ZP0"
  } else if ($2=="zpx") {
    ADDR_MODE="ZPX"
  } else if ($2=="zpy") {
    ADDR_MODE="ZPY"
  } else if ($2=="accum") { /* Accumulator address mode is essentialy the same as implied. */
    ADDR_MODE="IMP"
  }
}

NR!=1 && NR <=256 {
    print "  { \"" $1 "\", &R6502::" ADDR_MODE  ", &R6502::" $1 ", " $4 "},"
}

NR==257 {
    print "  { \"" $1 "\", &R6502::" ADDR_MODE  ", &R6502::" $1 ", " $4 "}"
}

END {
 print "}"
}
