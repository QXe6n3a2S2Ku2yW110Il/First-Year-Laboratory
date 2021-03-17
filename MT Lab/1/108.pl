#!/usr/bin/perl

while (<>) {
    print if /\([^\(\)]*\w+[^\(\)]*\)/
#    print if /\([.^[\(\)]]*\w+[.^[\(\)]]\)/
    # $s = <STDIN>
    # if ($s =~ /\b\(\w+\)\b/) {

    # }
}