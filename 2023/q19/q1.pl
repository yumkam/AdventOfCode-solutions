#!/usr/bin/perl -l
my %rules;
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
	warn qq{ sub { \$_[0]->{$1} $2 $3 } };
	push @r, [eval qq{ sub { \$_[0]->{$1} $2 $3 } },$4];
    }
    $rules{$name} = [\@r,$def];
}
my $res = 0;
while(<>) {
    chomp;
    s/^\{// or die $_;
    s/\}$// or die $_;
    my @F = split /,/;
    my %detail;
    my $sum = 0;
    for $d (@F) {
	my($var,$val)=split(/=/,$d);
	$detail{$var}=$val;
	$sum += $val;
    }
    my $name = 'in';
    while (length($name) > 1) {
	my $rule = $rules{$name};
	my $next = $rule->[1];
	for my $t (@{$rule->[0]}) {
	    if ($t->[0]->(\%detail)) {
		$next = $t->[1];
		last;
	    }
	}
	$name = $next;
    }
    warn "$sum $name";
    $res += $sum if $name eq 'A';
}
print $res;
