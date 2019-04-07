module Domain = Demo_Domain;
module Hy = Yawaramin_ReHyperapp;
include Hy.Component.Static;

type props = {.
  "currBook": option(Domain.bookId),
  "setCurrBook": (. Domain.bookId) => {. "currBook": option(Domain.bookId)},
  "book": Domain.book,
};

let make(~state as _=state, ~actions as _=actions, ~props, _children) = {
  let book = props##book;
  let bookId = book.Domain.id;

  let _class = "panel-block" ++ switch (props##currBook) {
    | Some(id) when id == bookId => " is-active"
    | _ => ""
  };

  let id = "item-" ++ book.Domain.id;
  let setCurrBook = props##setCurrBook;
  let onclick = (. _event) => setCurrBook(. bookId);

  let desc = {
    let author = book.Domain.author;
    if (author == "") "" else {j| · $author|j};
  };

  <a _class id key=id onclick>
    <span _class="panel-icon">{Hy.string({j|📖|j})}</span>
    {Hy.string(book.Domain.title ++ desc)}
  </a>;
};
