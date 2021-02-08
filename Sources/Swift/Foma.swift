//  Created by Lane Schwartz on 2021-02-08
//
import CFoma

struct Foma {
    static var text = "Hello, World!"

    static func foo(x: Int) -> String {

        let result = answer(Int32(x))

        return "\(text)\t\(result)"
    }
}
