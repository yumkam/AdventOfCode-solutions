#!/usr/bin/perl -l
use warnings;
use strict;
$_ = <>;
chomp;
s/^Time:\s*// or die;
s/\s+//g;
my $maxt = 0 + $_;
$_ = <>;
chomp;
s/^Distance:\s*// or die;
s/\s+//g;
my $maxd = 0 + $_;

{
    my $peak_time_1 = $maxt>>1;
    my $peak_time_2 = ($maxt+1)>>1;
    my $peak_dist = $peak_time_1*($maxt - $peak_time_1);
    die "$peak_dist < $maxd" if $peak_dist < $maxd;
    my $lo = 1;
    my $hi = $peak_time_1;
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
    $lo = $peak_time_2;
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
    print $end_time - $start_time;
=pod
    my $r = 0;
    for my $t0 (1..$maxt) {
	my $d = $t0*($maxt - $t0);
	++$r if $d > $maxd
    }
    print "$r\n";
=cut
}
