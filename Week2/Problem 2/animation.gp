set term gif animate delay 10
set output 'van_der_pol_animation.gif'

set title "Van der Pol Oscillator: y vs x with varying mu"
set xlabel "x"
set ylabel "y"
set xrange [-3:3]
set yrange [-3:3]

do for [i=1:39] {
    mu = sprintf("%.1f", i * 0.1)
    filename = sprintf("rk4_mu_%d.dat", i)
    plot filename using 2:3 with lines title sprintf("mu = %s", mu)
}
