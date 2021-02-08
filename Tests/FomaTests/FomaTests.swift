import XCTest
@testable import Foma

final class FomaTests: XCTestCase {
    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct
        // results.
        XCTAssertEqual(Foma.text, "Hello, World!")
        
    }

    func testOne() {
        XCTAssertEqual(Foma.foo(x: 1), "Hello, World!\t7")
    }

    func test42() {
        XCTAssertEqual(Foma.foo(x: 42), "Hello, World!\t42")
    }
    
    static var allTests = [
        ("testExample", testExample),
    ]
}
