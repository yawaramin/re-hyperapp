module Detail = Demo_Component_Detail;
module Domain = Demo_Domain;
module Hy = Yawaramin_ReHyperapp;

type props = unit;
type tab = [Domain.Status.t | `All];
type state = {.
  tab,
  books: Js.Dict.t(Domain.Book.t),
  currBookId: option(Domain.Book.id),
  detail: Js.t(Detail.state),
};
type setTab = (. tab) => {. "tab": tab};
type setCurrBookId =
  (. Domain.Book.id) => {. "currBookId": option(Domain.Book.id)};
type actions = {. setTab, setCurrBookId, detail: Js.t(Detail.actions)};
type tabProps = {. "currTab": tab, "newTab": tab, "setTab": setTab};

module Tab: Hy.Component.Type with type props = tabProps = {
  include Hy.Component.Static;

  type props = tabProps;

  let isActive(currTab, newTab) = if (currTab == newTab) "is-active" else "";

  let make(~state as _=state, ~actions as _=actions, ~props, _) = {
    let newTab = props##newTab;
    let setTab = props##setTab;

    <a _class=isActive(props##currTab, newTab) onclick={(. _event) => setTab(. newTab)}>
      {Hy.string(Domain.Status.(toEmoji(newTab) ++ " " ++ toString(newTab)))}
    </a>;
  };
};

// Dummy data
let books = Js.Dict.fromArray([|
  ("1", {
    "author": "J.R.R. Tolkien",
    "description": "The story of the fellowship of the races that overthrew the Dark Lord, and the great journey undertaken by two hobbits that made it possible.",
    "id": "1",
    "title": "The Lord of the Rings",
    "status": `Read,
  }),
  ("2", {
    "author": "Mikhail Bulgakov",
    "description": "The Devil comes to Stalin-era Moscow and wreaks havoc with his retinue of demons, while the Master struggles to finish his life's work (the story of Yeshua Ha-Nozri), and Margarita seeks a way to break free from the shackles of society and be reunited with her love.",
    "id": "2",
    "title": "The Master and Margarita",
    "status": `Read,
  }),
|]);

let state = {
  "tab": `All,
  "books": books,
  "currBookId": None,
  "detail": Detail.state,
};

let actions = {
  "setTab": (. tab) => {"tab": tab},
  "setCurrBookId": (. bookId) => {"currBookId": Some(bookId)},
  "detail": Detail.actions,
};

let tabProps(~currTab, ~newTab, ~setTab, ()) = {
  "currTab": currTab,
  "newTab": newTab,
  "setTab": setTab,
};

let make(~state=state, ~actions=actions, ~props as _, _) = {
  module Book = Demo_Component_Book;

  let setTab = actions##setTab;
  let books = state##books
    |> Js.Dict.values
    |> Array.map(book =>
      <Book props={
        "currBookId": state##currBookId,
        "setCurrBookId": actions##setCurrBookId,
        "book": book,
        "resetDetail": actions##detail##reset,
      } />)
    |> Hy.array;
  let currBook = state##currBookId |> Js.Option.andThen((. currBookId) =>
    Js.Dict.get(state##books, currBookId));

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
                <Tab props=tabProps(~currTab=state##tab, ~newTab=`All, ~setTab, ()) />
                <Tab props=tabProps(~currTab=state##tab, ~newTab=`ToRead, ~setTab, ()) />
                <Tab props=tabProps(~currTab=state##tab, ~newTab=`Reading, ~setTab, ()) />
                <Tab props=tabProps(~currTab=state##tab, ~newTab=`Read, ~setTab, ()) />
              </p>
              <a _class="panel-block">
                <span _class="panel-icon">{Hy.string({j|🆕|j})}</span>
                {Hy.string("Add New")}
              </a>
              {books}
            </nav>
          </div>
        </div>
        <Detail state=state##detail actions=actions##detail props=currBook />
      </div>
    </div>
  </section>;
};
