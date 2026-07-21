import XCTest
import SwiftTreeSitter
import TreeSitterSmali

final class TreeSitterSmaliTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_smali())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Smali grammar")
    }
}
