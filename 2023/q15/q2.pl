#!/usr/bin/perl -ln
sub debug (&) {}
#sub debug (&) {shift->()}
my @boxes=map {[]} 0..255;
sub hash($) {
    my $cur = 0;
    for my $c (unpack("C*", $_[0])) {
	$cur += $c;
	$cur *= 17;
	$cur &= 256-1;
    }
    return $cur;
}
for my $s (split /,/, $_) {
    debug { print STDERR $s };
    if ($s =~ s/-$//) {
	my $h = hash($s);
	$boxes[$h]=[grep {$_->[0] ne $s} @{$boxes[$h]}];
    } else {
	my($k,$v) = split /=/, $s;
	$v = 0+$v;
	my $h = hash($k);
	for my $x (@{$boxes[$h]}) {
	    if($x->[0] eq $k) {
		$x->[1] = $v;
		undef $k;
		last
	    }
	}
	if (defined $k) {
	    push @{$boxes[$h]}, [$k, $v]
	}
    }
    debug {
	for my $b (0..255) {
	    if (@{$boxes[$b]}) {
		print STDERR "Box $b: @{[map { qq{[@$_]} } @{$boxes[$b]}]}"
	    }
	}
	print STDERR "";
    };
}
my $sum = 0;
for my $b (0..255) {
    my $i = 0;
    for my $c (@{$boxes[$b]}) {
	$sum += ($b + 1)*++$i*$c->[1]
    }
}
print $sum
