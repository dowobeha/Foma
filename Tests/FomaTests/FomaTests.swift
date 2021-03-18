import XCTest
@testable import Foma

final class FomaTests: XCTestCase {
    
    // The following line of code is meant to obtain the absolute file path to the file FomaTests.fomabin
    //     In Swift, #file gives the path to this Swift file.
    //     We get the path to this file, then replace the suffix from .swift to .fomabin
    //     This assumes that this file and the fomabin file are in the same directory, which they should be.
    let testFile = URL(fileURLWithPath: #file.replacingOccurrences(of: ".swift", with: ".fomabin")).path // FileManager.default.currentDirectoryPath
    
    func applyUp(surfaceForm: String, underlyingForm: [String], using testFile: String) {
        if let fst = FST(fromBinary: testFile) {
            if let result = fst.applyUp(surfaceForm) {
                XCTAssertEqual(result.input, surfaceForm)
                XCTAssertEqual(result.outputs.count, underlyingForm.count)
                XCTAssertEqual(result.outputs, underlyingForm)
            } else {
                XCTFail("applyUp failed for \(surfaceForm)")
            }
        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }

    func testFomaVersion() {
        XCTAssertEqual(Foma.version, "0.9.18alpha")
    }
    
    func testAakaq()          { applyUp(surfaceForm: "aakaq",          underlyingForm: ["aakagh*(N)^[Abs.Sg]", "aag(V)^@~–(g)kagh(V→N)^[Abs.Sg]"], using: testFile) }
    func testAfsengaq()       { applyUp(surfaceForm: "afsengaq",       underlyingForm: ["afsengagh*(N)^[Abs.Sg]"], using: testFile) }
    func testAghnaghaq()      { applyUp(surfaceForm: "aghnaghaq",      underlyingForm: ["aghnaghagh*(N)^[Abs.Sg]"], using: testFile) }
    func testEltughaq()       { applyUp(surfaceForm: "eltughaq",       underlyingForm: ["eltughagh*(N)^[Abs.Sg]"], using: testFile) }
    func testNaliq()          { applyUp(surfaceForm: "naliq",          underlyingForm: ["naligh(WH)^[Abs.Sg]"], using: testFile) }
    func testNeghtuq()        { applyUp(surfaceForm: "neghtuq",        underlyingForm: ["negh(V)^[Ind.Intr]^[3Sg]"], using: testFile) }
    func testNengyuq()        { applyUp(surfaceForm: "nengyuq",        underlyingForm: ["nengyugh(N)^[Abs.Sg]", "nengyugh*(N)^[Abs.Sg]"], using: testFile) }
    func testNuziq()          { applyUp(surfaceForm: "nuziq",          underlyingForm: ["nuzigh(N)^[Abs.Sg]"], using: testFile) }
    func testPagungha()       { applyUp(surfaceForm: "pagungha",       underlyingForm: ["pagugh(V)^@~f–negh(V→N)^[Abs.3SgPoss.Sg]"], using: testFile) }
    func testPagunghaghmeng() { applyUp(surfaceForm: "pagunghaghmeng", underlyingForm: ["pagunghagh*(N)^[Abl_Mod.Sg]", "pagunghagh*(N)^[Rel.4DuPoss.Pl]", "pagunghagh*(N)^[Rel.4DuPoss.Sg]", "pagunghagh*(N)^[Rel.4PlPoss.Pl]", "pagunghagh*(N)^[Rel.4PlPoss.Sg]"], using: testFile) }
    func testPagunghaq()      { applyUp(surfaceForm: "pagunghaq",      underlyingForm: ["pagunghagh*(N)^[Abs.Sg]"], using: testFile) }
    func testQikmiq()         { applyUp(surfaceForm: "qikmiq",         underlyingForm: ["qikmigh(N)^[Abs.Sg]"], using: testFile) }
    func testTakestaaghhaq()  { applyUp(surfaceForm: "takestaaghhaq",  underlyingForm: ["takestaaghhagh*(N)^[Abs.Sg]", "takestaagh(N)^–ghhagh*(N→N)^[Abs.Sg]"], using: testFile) }
    func testTukuq()          { applyUp(surfaceForm: "tukuq",          underlyingForm: ["tukugh(N)^[Abs.Sg]", "tukugh*(N)^[Abs.Sg]"], using: testFile) }
    func testUyughaq()        { applyUp(surfaceForm: "uyughaq",        underlyingForm: ["uyughagh*(N)^[Abs.Sg]"], using: testFile) }

    func testSampleSentence() {
        
        if let fst = FST(fromBinary: testFile) {
            
            if let result = fst.applyUp("afsengaq") {
                XCTAssertEqual(result.input, "afsengaq")
                XCTAssertEqual(result.outputs, ["afsengagh*(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for afsengaq")
            }

            if let result = fst.applyUp("neghtuq") {
                XCTAssertEqual(result.input, "neghtuq")
                XCTAssertEqual(result.outputs, ["negh(V)^[Ind.Intr]^[3Sg]"])
            } else {
                XCTFail("applyUp failed for neghtuq")
            }

            if let result = fst.applyUp("pagunghaghmeng") {
                XCTAssertEqual(result.input, "pagunghaghmeng")
                XCTAssertEqual(result.outputs.count, 5)
            } else {
                XCTFail("applyUp failed for pagunghaghmeng")
            }
            
        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
 
    
    static var allTests = [
        ("testFomaVersion",    testFomaVersion),
        ("testAakaq",          testAakaq),
        ("testAfsengaq",       testAfsengaq),
        ("testAghnaghaq",      testAghnaghaq),
        ("testEltughaq",       testEltughaq),
        ("testNaliq",          testNaliq),
        ("testNeghtuq",        testNeghtuq),
        ("testNengyuq",        testNengyuq),
        ("testNuziq",          testNuziq),
        ("testPagungha",       testPagungha),
        ("testPagunghaghmeng", testPagunghaghmeng),
        ("testPagunghaq",      testPagunghaq),
        ("testQikmiq",         testQikmiq),
        ("testTakestaaghhaq",  testTakestaaghhaq),
        ("testTukuq",          testTukuq),
        ("testUyughaq",        testUyughaq),
        ("testSampleSentence", testSampleSentence),

    ]
}
