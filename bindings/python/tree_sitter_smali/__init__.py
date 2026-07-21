"""Smali grammar for tree-sitter"""

from importlib.resources import files as _files

from ._binding import language


def _get_query(name, file):
    try:
        query = _files(f"{__package__}") / file
        globals()[name] = query.read_text()
    except FileNotFoundError:
        globals()[name] = None
    return globals()[name]


def __getattr__(name):
    if name == "FOLDS_QUERY":
        return _get_query("FOLDS_QUERY", "queries/folds.scm")
    if name == "HIGHLIGHTS_QUERY":
        return _get_query("HIGHLIGHTS_QUERY", "queries/highlights.scm")
    if name == "INDENTS_QUERY":
        return _get_query("INDENTS_QUERY", "queries/indents.scm")
    if name == "INJECTIONS_QUERY":
        return _get_query("INJECTIONS_QUERY", "queries/injections.scm")
    if name == "LOCALS_QUERY":
        return _get_query("LOCALS_QUERY", "queries/locals.scm")
    if name == "TAGS_QUERY":
        return _get_query("TAGS_QUERY", "queries/tags.scm")

    raise AttributeError(f"module {__name__!r} has no attribute {name!r}")


__all__ = [
    "language",
    "FOLDS_QUERY",
    "HIGHLIGHTS_QUERY",
    "INDENTS_QUERY",
    "INJECTIONS_QUERY",
    "LOCALS_QUERY",
    "TAGS_QUERY",
]


def __dir__():
    return sorted(__all__ + [
        "__all__", "__builtins__", "__cached__", "__doc__", "__file__",
        "__loader__", "__name__", "__package__", "__path__", "__spec__",
    ])
