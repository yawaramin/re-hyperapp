module Domain = Demo_Domain;

include Yawaramin_ReHyperapp.Component.Type with
  type props = {.
    "currBook": option(Domain.bookId),
    "setCurrBook": (. Domain.bookId) => {. "currBook": option(Domain.bookId)},
    "book": Domain.book,
  };
