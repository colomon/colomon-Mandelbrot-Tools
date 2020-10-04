unit class colomon::Mandelbrot::Tools:ver<0.0.1>;


=begin pod

=head1 NAME

colomon::Mandelbrot::Tools - blah blah blah

=head1 SYNOPSIS

=begin code :lang<raku>

use colomon::Mandelbrot::Tools;

=end code

=head1 DESCRIPTION

colomon::Mandelbrot::Tools is ...

=head1 AUTHOR

Solomon Foster <colomon@gmail.com>

=head1 COPYRIGHT AND LICENSE

Copyright 2020 Solomon Foster

This library is free software; you can redistribute it and/or modify it under the Artistic License 2.0.

=end pod

sub write-header(IO::Handle $file, Complex $center, Num $view-width, Int $pixel-width, Int $iterations) is export {
    $file.say: "colomon Mandelbrot 1 { $center.re } { $center.im } { $view-width } $pixel-width $iterations";
}

sub read-header(@file-words) is export {
    my $tag1 = @file-words.shift;
    die unless $tag1 eq "colomon";
    my $tag2 = @file-words.shift;
    die unless $tag2 eq "Mandelbrot";
    my $version = @file-words.shift;
    die unless $version == 1;
    
    my $cr = @file-words.shift;
    my $ci = @file-words.shift;
    my $center = $cr + i * $ci;
    my $view-width = @file-words.shift;
    my $pixel-width = @file-words.shift;
    my $iterations = @file-words.shift;
    $center, $view-width, $pixel-width, $iterations;
}

sub write-body(IO::Handle $file, @lines) is export {
    for @lines -> $line {
        $file.say: $line.join(" ");
    }
}

sub read-body(@file-words, Int $pixel-width) is export {
    my @lines;
    for ^$pixel-width -> $line {
        my @line;
        for ^$pixel-width -> $word {
            @line.push: +@file-words[$line * $pixel-width + $word];
        }
        @lines.push(@line);
    }
    @lines;
}
