module Domain = Demo_Domain;

include Yawaramin_ReHyperapp.Component.Type with type props = {.
  "currBookId": option(Domain.Book.id),
  "setCurrBookId":
    (. Domain.Book.id) => {. "currBookId": option(Domain.Book.id)},
  "book": Domain.Book.t,
};
