#!/usr/bin/perl -ln
my $sum = 0;
for my $s (split /,/, $_) {
    my $cur = 0;
    for my $c (unpack("C*", $s)) {
	$cur += $c;
	$cur *= 17;
	$cur &= 256-1;
    }
    $sum += $cur;
}
print $sum;
