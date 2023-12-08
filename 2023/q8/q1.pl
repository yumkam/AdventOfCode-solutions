#!/usr/bin/perl -l
use warnings;
use strict;
my $inst = <>;
chomp($inst);
$inst =~ y/LR/01/;
my(@inst) = split //, $inst;
<>;
my %g;
while(<>) {
    chomp;
    /(...) = \((...), (...)\)/ or die;
    $g{$1} = [$2, $3];
}
my $node = 'AAA';
my $ret = 0;
my $p = 0;
while($node ne 'ZZZ') {
    ++$ret;
    $node = $g{$node}->[$inst[$p]];
    $p = 0 if ++$p == @inst;
}
print $ret
