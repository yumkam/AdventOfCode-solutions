#!/usr/bin/perl -l
use warnings;
use strict;
$_ = <>;
chomp;
s/^Time:\s*// or die;
my @times = split;
print "@{[@times]}\n";
$_ = <>;
chomp;
s/^Distance:\s*// or die;
my @dist = split;
print "@{[@dist]}\n";
my $n = $#times;
my $res = 1;
my $res2 = 1;
for my $i (0..$n) {
    my $maxt = $times[$i];
    my $maxd = $dist[$i];
    my $peak_time_1 = $maxt>>1;
    my $peak_time_2 = ($maxt+1)>>1;
    my $peak_dist_1 = $peak_time_1*($maxt - $peak_time_1);
    my $peak_dist_2 = $peak_time_2*($maxt - $peak_time_2);
    my($peak_time, $peak_dist) = $peak_dist_1 < $peak_dist_2 ? ($peak_time_2, $peak_dist_2) : ($peak_time_1, $peak_dist_1);
    die "$peak_dist < $maxd" if $peak_dist < $maxd;
    my $lo = 1;
    my $hi = $peak_time;
    while($lo < $hi) {
	my $mid = $lo + (($hi - $lo)>>1);
	my $dist = $mid*($maxt - $mid);
	if ($dist <= $maxd) {
	    $lo = $mid + 1;
	} else {
	    $hi = $mid;
	}
    }
    my $start_time = $lo;
    $lo = $peak_time_1;
    $hi = $maxt;
    while($lo < $hi) {
	my $mid = $lo + (($hi - $lo)>>1);
	my $dist = $mid*($maxt - $mid);
	if ($dist > $maxd) {
	    $lo = $mid + 1;
	} else {
	    $hi = $mid;
	}
    }
    my $end_time = $lo;
    $res2 *= $end_time - $start_time;
    print $end_time - $start_time, " ", $end_time, " ", $start_time, ' ', $maxt, ' ', $peak_time_1;
    my $r = 0;
    for my $t0 (1..$maxt) {
	my $d = $t0*($maxt - $t0);
	(printf "$t0 "), ++$r if $d > $maxd
    }
    print $r;
    $res *= $r;
}
print $res;
print $res2;
