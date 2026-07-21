package tree_sitter_smali_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_smali "github.com/tree-sitter-grammars/tree-sitter-smali/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_smali.Language())
	if language == nil {
		t.Errorf("Error loading Smali grammar")
	}
}
