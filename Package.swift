// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "Foma",
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "Foma",
            targets: ["Foma"]),
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
      Package.Dependency.package( // Needed for Swift package manager to see zlib
        url: "https://github.com/apple/swift-nio-zlib-support.git",
        from: "1.0.0"
      )
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .target(
            name: "CFoma",
            dependencies: [],
            path: "Sources/C"),
        .target(
            name: "Foma",
            dependencies: [
                .target(name: "CFoma")
            ],
            path: "Sources/Swift"),
        .testTarget(
            name: "FomaTests",
            dependencies: ["Foma"]),
    ]
)
