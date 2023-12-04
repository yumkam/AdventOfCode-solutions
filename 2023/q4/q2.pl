#!/usr/bin/perl -n
use warnings;
use strict;
chomp;
our @psum;
our $copies;
s/^Card +(\d+): // or die;
my $id = $1;
$copies -= $psum[$id] || 0;
our $sum;
my ($w,$p) = split /\|\s*/;
my %w;
@w{map {0+$_} split ' ', $w} = ();
my $score = grep {exists $w{$_}} map {0+$_} split ' ', $p;
$sum += 1 + $copies;
#warn "$id ", 1 + $copies;
$psum[$id + $score + 1] += 1 + $copies;
$copies += 1 + $copies;
END {
    print $sum
}
