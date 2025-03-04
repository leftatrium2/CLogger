import Foundation

protocol CLoggerT {
    func tag() -> String
}

public class CLoggerConfig{
    private var logan: Bool
    private var loganUseFakeTime: Bool
    private var loganDir: String?
    private var loganCacheDir: String?
    private var loganMaxFile: Int
    private var loganMaxDay: Int
    private var loganIsDebug: Bool
    
    private var printable: Bool
    
    private var saveToDisk: Bool
    private var saveToDiskLogDir: String?
    
    init() {
        self.logan = false
        self.loganUseFakeTime = true
        self.loganDir = nil
        self.loganCacheDir = nil
        self.loganMaxFile = 0
        self.loganMaxDay = 0
        self.loganIsDebug = false
        
        self.printable = true
        
        self.saveToDisk = false
        self.saveToDiskLogDir = nil
    }
    
    func logan(logan: Bool) -> CLoggerConfig {
        self.logan = logan
        return self
    }
    
    func loganUseFakeTime(loganUseFakeTime: Bool) -> CLoggerConfig {
        self.loganUseFakeTime = loganUseFakeTime
        return self
    }
    
    func loganDir(loganDir: String) -> CLoggerConfig {
        self.loganDir = loganDir
        return self
    }
    
    func printable(printable:Bool) -> CLoggerConfig {
        self.printable = printable
        return self
    }
}


public class CLogger{
    
}
