BEGIN {
  FS=","
  print "{"
}

NR!=1 && NR <=256 {
    print $4 ","
}

NR==257 {
    print $4
}

END {
 print "}"
}
