module Domain = Demo_Domain;
module Hy = Yawaramin_ReHyperapp;
include Hy.Component.Static;

type props = {.
  "currBookId": option(Domain.Book.id),
  "setCurrBookId":
    (. Domain.Book.id) => {. "currBookId": option(Domain.Book.id)},
  "book": Domain.Book.t,
};

let make(~state as _=state, ~actions as _=actions, ~props, _children) = {
  let book = props##book;
  let bookId = book##id;

  let _class = "panel-block" ++ switch (props##currBookId) {
    | Some(id) when id == bookId => " is-active"
    | _ => ""
  };

  let id = "item-" ++ bookId;
  let setCurrBookId = props##setCurrBookId;
  let onclick = (. _event) => setCurrBookId(. bookId);

  let desc = {
    let author = book##author;
    if (author == "") "" else {j| · $author|j};
  };

  <a _class id key=id onclick>
    <span _class="panel-icon">{Hy.string({j|📖|j})}</span>
    {Hy.string(book##title ++ desc)}
  </a>;
};