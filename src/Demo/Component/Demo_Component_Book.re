module Domain = Demo_Domain;
module Hy = Yawaramin_ReHyperapp;

type props = Domain.book;
type state = unit;
type actions = unit;

let state = Hy.empty();
let actions = Hy.empty();

let make(~state as _=state, ~actions as _=actions, ~props as book, _) = {
  let desc = {
    let desc = book.Domain.description;
    if (desc == "") Hy.null
    else <span _class="has-text-grey">{Hy.string({j|: $desc|j})}</span>;
  };

  <a _class="panel-block">
    <span _class="panel-icon">{Hy.string({j|📖|j})}</span>
    {Hy.string(book.Domain.title)}
    {desc}
  </a>;
};
