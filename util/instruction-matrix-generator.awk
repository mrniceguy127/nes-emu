BEGIN {
  FS=","
  print "{"
}

NR!=1 {
  OP=$1 "   "
  if ($1=="ILLEGAL") {
    OP="NULLOP"
  }

  ADDR_MODE="NULLMODE   "
  if ($2=="relative") {
    ADDR_MODE="RELATIVE   "
  } else if ($2=="abs") {
    ADDR_MODE="ABSOLUTE   "
  } else if ($2=="absx") {
    ADDR_MODE="ABSOLUTEX  "
  } else if ($2=="absy") {
    ADDR_MODE="ABSOLUTEY  "
  } else if ($2=="ind") {
    ADDR_MODE="INDIRECT   "
  } else if ($2=="indx") {
    ADDR_MODE="INDIRECTX  "
  } else if ($2=="indy") {
    ADDR_MODE="INDIRECTY  "
  } else if ($2=="imm") {
    ADDR_MODE="IMMEDIATE  "
  } else if ($2=="implied") {
    ADDR_MODE="IMPLIED    "
  } else if ($2=="zp") {
    ADDR_MODE="ZEROPAGE   "
  } else if ($2=="zpx") {
    ADDR_MODE="ZEROPAGEX  "
  } else if ($2=="zpy") {
    ADDR_MODE="ZEROPAGEY  "
  } else if ($2=="accum") {
    ADDR_MODE="ACCUMULATOR"
  }
}

NR!=1 && NR <=256 {
    print "  { " ADDR_MODE  ", " OP " },"
}

NR==257 {
    print "  { " ADDR_MODE  ", " OP " }"
}

END {
 print "}"
}
