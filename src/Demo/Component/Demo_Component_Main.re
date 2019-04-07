module Domain = Demo_Domain;
module Hy = Yawaramin_ReHyperapp;

type tab = All | ToRead | Reading | Read;
type props = unit;

type state = {.
  tab,
  books: Js.Dict.t(Domain.book),
  currBook: option(Domain.bookId),
};

type setTab = (. tab) => {. "tab": tab};
type setCurrBook = (. Domain.bookId) => {. "currBook": option(Domain.bookId)};
type actions = {. setTab, setCurrBook};

type tabProps = {.
  "currTab": tab,
  "newTab": tab,
  "label": string,
  "setTab": setTab,
};

module Tab: Hy.Component.Type with type props = tabProps = {
  include Hy.Component.Static;

  type props = tabProps;

  let isActive(currTab, newTab) = if (currTab == newTab) "is-active" else "";

  let make(~state as _=state, ~actions as _=actions, ~props, _) = {
    let setTab = props##setTab;

    <a _class=isActive(props##currTab, props##newTab) onclick={(. _event) => setTab(. props##newTab)}>
      {Hy.string(props##label)}
    </a>;
  };
};

// Dummy data
let books = Js.Dict.fromArray(Domain.[|
  ("1", {author: "J.R.R. Tolkien", available: 3, copies: 10, description: "The story of the fellowship of the races that overthrew the Dark Lord, and the great journey undertaken by two hobbits that made it possible.", id: "1", title: "The Lord of the Rings", status: `quo}),
  ("2", {author: "Mikhail Bulgakov", available: 2, copies: 2, description: "The Devil comes to Stalin-era Moscow and wreaks havoc with his retinue of demons, while the Master struggles to finish his life's work (the story of Yeshua Ha-Nozri), and Margarita seeks a way to break free from the shackles of society and be reunited with her love.", id: "2", title: "The Master and Margarita", status: `quo}),
|]);

let state = {"tab": All, "books": books, "currBook": None};

let actions = {
  "setTab": (. tab) => {"tab": tab},
  "setCurrBook": (. bookId) => {"currBook": Some(bookId)},
};

let tabProps(~currTab, ~newTab, ~label, ~setTab, ()) = {
  "currTab": currTab,
  "newTab": newTab,
  "label": label,
  "setTab": setTab,
};

let make(~state=state, ~actions=actions, ~props as _, _) = {
  module Book = Demo_Component_Book;

  let setTab = actions##setTab;
  let books = state##books
    |> Js.Dict.values
    |> Array.map(book =>
      <Book props={
        "currBook": state##currBook,
        "setCurrBook": actions##setCurrBook,
        "book": book,
      } />)
    |> Hy.array;

  <section>
    <nav _class="level">
      <div _class="level-item has-text-centered">
        <h1 style="margin-top: .75rem" _class="title">
          {Hy.string({j|🏫 My Library|j})}
        </h1>
      </div>
    </nav>
    <div _class="container is-fluid">
      <div _class="tile is-ancestor">
        <div _class="tile is-4 is-parent">
          <div _class="tile is-child">
            <nav _class="panel">
              <div _class="panel-block">
                <p _class="control has-icons-left">
                  <input _class="input is-small" _type="text" placeholder="Filter" />
                  <span _class="icon is-small is-left">{Hy.string({j|🔍|j})}</span>
                </p>
              </div>
              <p _class="panel-tabs">
                <Tab props=tabProps(~currTab=state##tab, ~newTab=All, ~label={j|📚 all|j}, ~setTab, ()) />
                <Tab props=tabProps(~currTab=state##tab, ~newTab=ToRead, ~label={j|📘 to read|j}, ~setTab, ()) />
                <Tab props=tabProps(~currTab=state##tab, ~newTab=Reading, ~label={j|📖 reading|j}, ~setTab, ()) />
                <Tab props=tabProps(~currTab=state##tab, ~newTab=Read, ~label={j|📗 read|j}, ~setTab, ()) />
              </p>
              <a _class="panel-block">
                <span _class="panel-icon">{Hy.string({j|🆕|j})}</span>
                {Hy.string("Add New")}
              </a>
              {books}
            </nav>
          </div>
        </div>
        <div _class="tile is-parent">
          <div _class="tile is-child box">
            {Hy.string("Test!")}
          </div>
        </div>
      </div>
    </div>
  </section>;
};
