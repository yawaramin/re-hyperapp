module Domain = Demo_Domain;
module Hy = Yawaramin_ReHyperapp;
include Hy.Component.Static;

type props = Domain.book;

let make(~state as _=state, ~actions as _=actions, ~props as book, _) = {
  let desc = {
    let author = book.Domain.author;
    if (author == "") "" else {j| · $author|j};
  };

  let id = "item-" ++ string_of_int(book.Domain.id);

  <a _class="panel-block" id key=id href={"#" ++ id}>
    <span _class="panel-icon">{Hy.string({j|📖|j})}</span>
    {Hy.string(book.Domain.title ++ desc)}
  </a>;
};
