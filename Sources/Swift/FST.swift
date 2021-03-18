import CFoma

public class FST {
    private var fsmPointer : UnsafeMutablePointer<fsm>
    //private var applyHandle: UnsafeMutablePointer<apply_handle>
    
    public static var defHandle = defined_networks_init()
    public static var deffHandle = defined_functions_init()
    
    public init?(fromBinary binaryFilename: String) {
            
        let possiblyNullPointer: UnsafeMutablePointer<fsm>? = binaryFilename.withCString { (binaryFilenameAsCString:UnsafePointer<CChar>) -> UnsafeMutablePointer<fsm>? in
            if let result = fsm_read_binary_file(UnsafeMutablePointer<CChar>(mutating: binaryFilenameAsCString)) {
                return result
            } else {
                return nil
            }
        }
        
        if let pointer = possiblyNullPointer {
            self.fsmPointer = pointer
        } else {
            return nil
        }
        
    }
    
    private init(fromPointer unsafeMutablePointer: UnsafeMutablePointer<fsm>) {
        self.fsmPointer = unsafeMutablePointer
        //self.applyHandle = apply_init(fsmPointer)
    }
    
    deinit {
        //apply_clear(self.applyHandle)
        fsm_destroy(self.fsmPointer)
    }
    
    private func apply(function applyFunction: Foma.BinaryApplyFunction, to string:String) -> Result? {
        
        
        if let applyHandle = apply_init(fsmPointer) {
            defer {
                apply_clear(applyHandle)
            }
            var results = [String]()
            
            let result = string.withCString  { (cString:UnsafePointer<CChar>) -> Result? in
                if let firstResult: UnsafeMutablePointer<CChar> = applyFunction(applyHandle, UnsafeMutablePointer<CChar>(mutating: cString)) {
                    results.append(String(cString: firstResult))
                    
                    let nullPointer = UnsafeMutablePointer<CChar>(nil)
                    while let nextResult: UnsafeMutablePointer<CChar> = applyFunction(applyHandle, nullPointer) {
                        results.append(String(cString: nextResult))
                    }
                    return Result(input: string, outputs: results)
                } else {
                    return nil
                }
            }
            return result
        }

        return nil
    }
    
    private func apply(function applyFunction: Foma.UnaryApplyFunction) -> String? {
        
        if let applyHandle = apply_init(fsmPointer) {
            defer {
                apply_clear(applyHandle)
            }
            if let result = applyFunction(applyHandle) {
                return String(cString: result)
            } else {
                return nil
            }
        } else {
            return nil
        }
    }

    private func read(function readFunction: Foma.ReadHandleToIntFunction) -> Int {
        let readHandle: UnsafeMutablePointer<fsm_read_handle> = fsm_read_init(self.fsmPointer)
        defer {
            fsm_read_done(readHandle)
        }
        return Int(readFunction(readHandle))
    }
    
    public func applyUp(_ s: String, lowercaseBackoff : Bool = true, removePunctBackoff : Bool = true) -> Result? {
        if let results = self.apply(function: apply_up, to: s) {
            return results
        } else if                             removePunctBackoff == true, let results = self.apply(function: apply_up, to: String(s.filter{!$0.isPunctuation})) {
            return results
        } else if lowercaseBackoff == true && removePunctBackoff == true, let results = self.apply(function: apply_up, to: String(s.lowercased().filter{!$0.isPunctuation})) {
            return results
        } else if lowercaseBackoff == true && removePunctBackoff == false, let results = self.apply(function: apply_up, to: String(s.lowercased())) {
            return results
        } else {
            return nil
        }
    }
    
    public func applyDown(_ s: String) -> Result? {
        if let results = self.apply(function: apply_down, to: s) {
            return results
        } else {
            return nil
        }
    }
    
    public func randomLower() -> String? {
        return self.apply(function: apply_random_lower)
    }

    public func randomUpper() -> String? {
        return self.apply(function: apply_random_upper)
    }
    
    public func numStates() -> Int {
        return self.read(function: fsm_get_num_states)
    }
    
    public func union(_ other: FST) -> FST {
        return FST(fromPointer: fsm_union(self.fsmPointer, other.fsmPointer))
    }
    
}
