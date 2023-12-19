#!/usr/bin/perl -l
use strict;
use warnings;
my %rules;
my %tr;
$tr{'x'} = 0;
$tr{'m'} = 1;
$tr{'a'} = 2;
$tr{'s'} = 3;
while(<>) {
    chomp;
    last unless length $_;
    s/^([a-z]+)// or die $_;
    my $name = $1;
    s/^\{// or die $_;
    s/\}$// or die $_;
    my @F = split /,/;
    my $def = pop @F;
    my @r;
    for my $rule (@F) {
	$rule =~ /^([xmas])([<>])(\d+):([AR]|[a-z]+)$/ or die $rule;
	push @r, [$tr{$1}, $2, int($3),$4];
    }
    $rules{$name} = [\@r,$def];
}
my $res = 0;
sub min($$) { $_[0] < $_[1] ? $_[0] : $_[1] }
sub max($$) { $_[0] > $_[1] ? $_[0] : $_[1] }
sub dfs($$$);
sub dfs($$$) {
    my ($name, $mins, $maxs) = @_;
    #warn "$name, @$mins, @$maxs";
    for my $i (0..$#$mins) {
	return if $mins->[$i] > $maxs->[$i]
    }
    if (length($name) == 1) {
	return if $name eq 'R';
	my $r = 1;
	for my $i (0..$#$mins) {
	    $r *= $maxs->[$i] - $mins->[$i] + 1
	}
	$res += $r;
	return;
    }
    $mins = [@$mins];
    $maxs = [@$maxs];
    my $rule = $rules{$name};
    for my $x (@{$rule->[0]}) {
	my($id,$op,$val,$dest) = @$x;
	$val = int($val);
	#warn "$id $mins->[$id] $maxs->[$id] $op $val";
	if ($op eq '>') {
	    my $save = $mins->[$id];
	    $mins->[$id] = max($mins->[$id], $val + 1);
	    dfs($dest,$mins,$maxs);
	    $mins->[$id] = $save;
	    $val = min($val, $maxs->[$id]);
	    $maxs->[$id] = $val;
	    last if $save > $val;
	} else {
	    my $save = $maxs->[$id];
	    $maxs->[$id] = min($maxs->[$id], $val - 1);
	    dfs($dest,$mins,$maxs);
	    $maxs->[$id] = $save;
	    $val = max($val, $mins->[$id]);
	    $mins->[$id] = $val;
	    last if $val > $save;
	}
    }
    dfs($rule->[1],$mins,$maxs);
}
dfs('in',[(1) x 4],[(4000) x 4]);
print $res;
