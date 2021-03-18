import XCTest
@testable import Foma

final class FomaTests: XCTestCase {
    func testFomaVersion() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct
        // results.
        XCTAssertEqual(Foma.version, "0.9.18alpha")
    }

    func testFomaReadBinaryFile() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {
            if let result = fst.applyUp("qikmiq") {
                XCTAssertEqual(result.input, "qikmiq")
                XCTAssertEqual(result.outputs, ["qikmigh(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed")
            }
        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }

    
    func testAfsengaq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {
            
            if let result = fst.applyUp("afsengaq") {
                XCTAssertEqual(result.input, "afsengaq")
                XCTAssertEqual(result.outputs, ["afsengagh*(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for afsengaq")
            }
            
        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }

    func testNeghtuq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("neghtuq") {
                XCTAssertEqual(result.input, "neghtuq")
                XCTAssertEqual(result.outputs, ["negh(V)^[Ind.Intr]^[3Sg]"])
            } else {
                XCTFail("applyUp failed for neghtuq")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
    
    func testPagungha() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("pagungha") {
                XCTAssertEqual(result.input, "pagungha")
                XCTAssertEqual(result.outputs, ["pagugh(V)^@~f–negh(V→N)^[Abs.3SgPoss.Sg]"])
            } else {
                XCTFail("applyUp failed for pagungha")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
    
    func testNengyuq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("nengyuq") {
                XCTAssertEqual(result.input, "nengyuq")
                XCTAssertEqual(result.outputs.count, 2)
                XCTAssertEqual(result.outputs, ["nengyugh(N)^[Abs.Sg]", "nengyugh*(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for nengyuq")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
    
    func testEltughaq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("eltughaq") {
                XCTAssertEqual(result.input, "eltughaq")
                XCTAssertEqual(result.outputs.count, 1)
                XCTAssertEqual(result.outputs, ["eltughagh*(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for eltughaq")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }

    func testUyughaq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            let word = "uyughaq"
            
            if let result = fst.applyUp(word) {
                XCTAssertEqual(result.input, word)
                XCTAssertEqual(result.outputs.count, 1)
                XCTAssertEqual(result.outputs, ["uyughagh*(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for \(word)")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
    
    func testNaliq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            let word = "naliq"
            
            if let result = fst.applyUp(word) {
                XCTAssertEqual(result.input, word)
                XCTAssertEqual(result.outputs.count, 1)
                XCTAssertEqual(result.outputs, ["naligh(WH)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for \(word)")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }

    
    func testNuziq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            let word = "nuziq"
            
            if let result = fst.applyUp(word) {
                XCTAssertEqual(result.input, word)
                XCTAssertEqual(result.outputs.count, 1)
                XCTAssertEqual(result.outputs, ["nuzigh(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for \(word)")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
    
    func testAakaq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("aakaq") {
                XCTAssertEqual(result.input, "aakaq")
                XCTAssertEqual(result.outputs.count, 2)
                XCTAssertEqual(result.outputs, ["aakagh*(N)^[Abs.Sg]", "aag(V)^@~–(g)kagh(V→N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for aakaq")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }

    func testTukuq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("tukuq") {
                XCTAssertEqual(result.input, "tukuq")
                XCTAssertEqual(result.outputs.count, 2)
                XCTAssertEqual(result.outputs, ["tukugh(N)^[Abs.Sg]", "tukugh*(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for tukuq")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
    
    
    
    func testAghnaghaq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("aghnaghaq") {
                XCTAssertEqual(result.input, "aghnaghaq")
                XCTAssertEqual(result.outputs.count, 1)
                XCTAssertEqual(result.outputs, ["aghnaghagh*(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for aghnaghaq")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
 
    
    func testTakestaaghhaq() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("takestaaghhaq") {
                XCTAssertEqual(result.input, "takestaaghhaq")
                XCTAssertEqual(result.outputs.count, 2)
                XCTAssertEqual(result.outputs, ["takestaaghhagh*(N)^[Abs.Sg]", "takestaagh(N)^–ghhagh*(N→N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for takestaaghhaq")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
 

    func testPagunghaq() {
        let testFile = "/Users/lanes/finite_state_morphology/pagunghaq.fomabin"
        if let fst = FST(fromBinary: testFile) {

            if let result = fst.applyUp("pagunghaq") {
                XCTAssertEqual(result.input, "pagunghaq")
                XCTAssertEqual(result.outputs, ["pagunghagh*(N)^[Abs.Sg]"])
            } else {
                XCTFail("applyUp failed for pagunghaq")
            }

        } else {
            XCTFail("Failed to read binary file \(testFile)")
        }
    }
   
    
    func testPagunghaghmeng() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
        if let fst = FST(fromBinary: testFile) {
            
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
 

    
    func testSampleSentence() {
        let testFile = "/Users/lanes/finite_state_morphology/l2s.fomabin"
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
        ("testFomaVersion", testFomaVersion),
    ]
}
