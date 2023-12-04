#!/usr/bin/perl -n
use warnings;
use strict;
chomp;
s/^Card +(\d+): // or die;
my $id = $1;
our $sum;
my ($w,$p) = split /\|\s*/;
my %w;
@w{map {0+$_} split ' ', $w} = ();
my $shift = grep {exists $w{$_}} map {0+$_} split ' ', $p;
$sum += 1 << ($shift - 1) if $shift;
END {
    print $sum
}
