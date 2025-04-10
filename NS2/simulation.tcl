# Create simulator object
set ns [new Simulator]

# Open trace and nam files
set tra [open tracefile.tr w]
set namf [open namfile.nam w]

$ns trace-all $tra
$ns namtrace-all $namf

# Assign colors
$ns color 1 Blue
$ns color 2 Green
$ns color 3 Red

# Define finish procedure
proc finish {} {
    global ns tra namf
    $ns flush-trace
    close $tra
    close $namf
    exec nam namfile.nam &
    exit 0
}

# Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]

# Create links
$ns duplex-link $n0 $n3 1Mb 10ms DropTail
$ns duplex-link $n1 $n3 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail
$ns duplex-link $n4 $n5 1Mb 10ms DropTail
$ns duplex-link $n4 $n6 1Mb 10ms DropTail
$ns duplex-link $n4 $n7 1Mb 10ms DropTail

# Set orientation (for NAM display)
$ns duplex-link-op $n0 $n3 orient right-down
$ns duplex-link-op $n1 $n3 orient right
$ns duplex-link-op $n2 $n3 orient right-up
$ns duplex-link-op $n3 $n4 orient right
$ns duplex-link-op $n4 $n5 orient right-up
$ns duplex-link-op $n4 $n6 orient right
$ns duplex-link-op $n4 $n7 orient right-down

# Set queue limit
$ns queue-limit $n3 $n4 30

# Create TCP and attach to node n0
set tcp0 [new Agent/TCP]
$tcp0 set fid_ 1
$ns attach-agent $n0 $tcp0

# Create UDP agents
set udp1 [new Agent/UDP]
$udp1 set fid_ 2
$ns attach-agent $n1 $udp1

set udp2 [new Agent/UDP]
$udp2 set fid_ 3
$ns attach-agent $n2 $udp2

# Create sinks
set sink0 [new Agent/TCPSink]
$ns attach-agent $n5 $sink0

set sink1 [new Agent/Null]
$ns attach-agent $n6 $sink1

set sink2 [new Agent/Null]
$ns attach-agent $n7 $sink2

# Connect agents
$ns connect $tcp0 $sink0
$ns connect $udp1 $sink1
$ns connect $udp2 $sink2

# Applications
set ftp0 [new Application/FTP]
$ftp0 set packetSize_ 500
$ftp0 attach-agent $tcp0

set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.01
$cbr1 attach-agent $udp1

set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 500
$cbr2 set interval_ 0.01
$cbr2 attach-agent $udp2

# Scheduling events
$ns at 0.1 "$ftp0 start"
$ns at 0.2 "$cbr1 start"
$ns at 0.3 "$cbr2 start"

$ns at 8.0 "$ftp0 stop"
$ns at 9.0 "$cbr1 stop"
$ns at 9.55 "$cbr2 stop"
$ns at 10.0 "finish"

# Run the simulation
$ns run

