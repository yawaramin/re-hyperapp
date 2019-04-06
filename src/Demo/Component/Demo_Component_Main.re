module Domain = Demo_Domain;
module Hy = Yawaramin_ReHyperapp;

type tab = All | ToRead | Reading | Read;
type props = unit;
type state = {. tab, books: array(Domain.book)};
type setTab = (. tab) => (. state) => {. "tab": tab};
type actions = {. setTab: setTab};
type tabProps = {currTab: tab, newTab: tab, label: string, setTab};

module Tab: Hy.Component with type props = tabProps = {
  type props = tabProps;
  type state = unit;
  type actions = unit;

  let state = Hy.empty();
  let actions = Hy.empty();
  let isActive(currTab, newTab) = if (currTab == newTab) "is-active" else "";

  let make(~state as _=state, ~actions as _=actions, ~props, _) =
    <a _class=isActive(props.currTab, props.newTab) onclick={(. _event) => props.setTab(. props.newTab)}>
      {Hy.string(props.label)}
    </a>;
};

// Dummy data
let books = Domain.[|
  {author: "J.R.R. Tolkien", available: 3, copies: 10, description: "The story of the fellowship of the races that overthrew the Dark Lord, and the great journey undertaken by two hobbits that made it possible.", id: 1, title: "The Lord of the Rings", status: `quo},
  {author: "Mikhail Bulgakov", available: 2, copies: 2, description: "The Devil comes to Stalin-era Moscow and wreaks havoc with his retinue of demons, while the Master struggles to finish his life's work (the story of Yeshua Ha-Nozri), and Margarita seeks a way to break free from the shackles of society and be reunited with her love.", id: 1, title: "The Master and Margarita", status: `quo},
|];

let state = {"tab": All, "books": books};
let actions = {"setTab": (. tab) => (. _state) => {"tab": tab}};

let make(~state=state, ~actions=actions, ~props as _, _) = {
  module Book = Demo_Component_Book;

  let setTab = actions##setTab;
  let books = state##books
    |> Array.map(book => <Book props=book />)
    |> Hy.array;

  <nav _class="panel">
    <p _class="panel-heading">{Hy.string("My Library")}</p>
    <div _class="panel-block">
      <p _class="control has-icons-left">
        <input _class="input is-small" _type="text" placeholder="Filter" />
        <span _class="icon is-small is-left">{Hy.string({j|🔍|j})}</span>
      </p>
    </div>
    <p _class="panel-tabs">
      <Tab props={currTab: state##tab, newTab: All, label: {j|📚 all|j}, setTab} />
      <Tab props={currTab: state##tab, newTab: ToRead, label: {j|📘 to read|j}, setTab} />
      <Tab props={currTab: state##tab, newTab: Reading, label: {j|📖 reading|j}, setTab} />
      <Tab props={currTab: state##tab, newTab: Read, label: {j|📗 read|j}, setTab} />
    </p>
    <a _class="panel-block">
      <span _class="panel-icon">{Hy.string({j|🆕|j})}</span>
      {Hy.string("New item")}
    </a>
    {books}
  </nav>
};
