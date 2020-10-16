unit class colomon::Mandelbrot::Tools:ver<0.0.1>;
use NativeCall;

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

sub use-if-there($a) {
    $a ne "" ?? ($a) !! ();
}

sub compile_c_lib($name) is export {
    my (@c_line, @l_line);
    my $VM  := $*VM;
    my $cfg := $VM.config;
    my $libname = $VM.platform-library-name($name.IO);
    if $VM.name eq 'moar' {
        my $o  = $cfg<obj>;

        # MoarVM exposes exposes GNU make directives here, but we cannot pass this to gcc directly.
        my $ldshared = $cfg<ldshared>.subst(/'--out-implib,lib$(notdir $@).a'/, "--out-implib,$libname.a");
        @c_line = $cfg<cc>, "-c", |use-if-there($cfg<ccshared>), $cfg<ccout>.trim, $name ~ $o,
                  |$cfg<cflags>.split(/\s+/), "lib/colomon/Mandelbrot/$name.cpp";
        @l_line = $cfg<ld>, $ldshared, |$cfg<ldflags>.trim.split(/\s+/), |$cfg<ldlibs>.trim.split(/\s+/),
                  $cfg<ldout>.trim, $libname.Str, $name ~ $o;
    }
    # elsif $VM.name eq 'jvm' || $VM.name eq 'js' {
    #     $c_line = "$cfg<nativecall.cc> -c $cfg<nativecall.ccdlflags> -o$name$cfg<nativecall.o> $cfg<nativecall.ccflags> t/04-nativecall/$name.c";
    #     $l_line = "$cfg<nativecall.ld> $cfg<nativecall.perllibs> $cfg<nativecall.lddlflags> $cfg<nativecall.ldflags> $cfg<nativecall.ldout>$libname $name$cfg<nativecall.o>";
    #     @cleanup = << $libname "$name$cfg<nativecall.o>" >>;
    # }
    else {
        die "Unknown VM; don't know how to compile test libraries";
    }
    dd @c_line;
    run @c_line;
    dd @l_line;
    run @l_line;
}

my $tools-has-been-compiled = False;

sub make-sure-tools-compiled {
    compile_c_lib("tools") unless $tools-has-been-compiled;
    $tools-has-been-compiled = True;
}

sub mandel_double(num64, num64, uint32) returns uint32 is native('./tools') { * }

sub mandel(Complex $c, $max-iterations) is export {
    make-sure-tools-compiled;
    mandel_double($c.re, $c.im, $max-iterations);
    
    # my $z = 0i;
    # my $i;
    # loop ($i = 0; $i < $max-iterations; $i++) {
    #     if ($z.abs > 2) {
    #         return $i + 1;
    #     }
    #     $z = $z * $z + $c;
    # }
    # return 0;
}

sub modified_log_color_c(uint32, uint32 is rw, uint32 is rw, uint32 is rw) is native('./tools') { * }

sub modified-log-color($pixel) is export {
    make-sure-tools-compiled;
    # my uint32 ($red, $green, $blue);
    my $color = modified_log_color_c($pixel, my uint32 $red, my uint32 $green, my uint32 $blue);
    "$red $green $blue";

    # if $pixel < 64 {
    #     my $low = $pixel div 16;
    #     my $high = $low + 1;
    #     my $fraction = (1 / 16) * ($pixel % 16);
    #     linear-blend-color(@color_map[$low], @color_map[$high], $fraction);
    # } else {
    #     my $log-pixel = $pixel.log(2) - 2;
    #     my $low = $log-pixel.floor;
    #     my $high = $log-pixel.ceiling;
    #     my $fraction = $log-pixel - $low;
    #     linear-blend-color(@color_map[$low], @color_map[$high], $fraction);
    # }
}


sub write-header(IO::Handle $file, Complex $center, Real $view-width, Int $pixel-width, Int $iterations) is export {
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
