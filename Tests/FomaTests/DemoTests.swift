import XCTest
@testable import Foma

final class DemoTests: XCTestCase {
    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct
        // results.
        XCTAssertEqual(Demo.text, "Hello, World!")
        
    }

    func testOne() {
        XCTAssertEqual(Demo.foo(x: 1), "Hello, World!\t7")
    }

    func test42() {
        XCTAssertEqual(Demo.foo(x: 42), "Hello, World!\t42")
    }
    
    static var allTests = [
        ("testExample", testExample),
    ]
}
