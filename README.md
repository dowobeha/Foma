# Foma

A [Swift](https://swift.org) wrapper for [foma](https://github.com/mhulden/foma/tree/master/foma).


## Usage:

Add the following to the ```dependencies``` section of your Package.swift file:

```
.package(
    name: "Foma",
    url: "https://github.com/dowobeha/Foma.git",
    from: "0.3.5"),
.package( // Needed for Swift package manager to see zlib
    url: "https://github.com/apple/swift-nio-zlib-support.git",
    from: "1.0.0"
)
```
