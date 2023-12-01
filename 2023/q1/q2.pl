#!/usr/bin/perl -ln
BEGIN {
    @m{qw/one two three four five six seven eight nine/,1..9}=(1..9,1..9);$m=join("|",keys %m);
    while(my($k,$v) = each %m) { $M{reverse($k)}=$v } $M=join("|",keys %M);
}
$s += $m{scalar(/$m/o, $&)}.$M{scalar(reverse($_) =~ /$M/o, $&)};
END {
    print $s
}
