/** Sample app to show how to idiomatically structure a ReHyperapp
    project. It's mostly the same as a normal Hyperapp project, just with
    more types. */

module Component = Yawaramin_ReHyperapp_Demo_Component;
module Domain = Yawaramin_ReHyperapp_Demo_Domain;
module Hyperapp = Yawaramin_ReHyperapp;

type state = {.
  "nav": Component.Nav.state,
  "bookList": Component.BookList.state,
};

let state = {
  "nav": Component.Nav.state,
  "bookList": Component.BookList.state,
};

let actions = {
  "nav": Component.Nav.actions,
  "bookList": Component.BookList.actions,
};

let view(. state, actions) =
  <div>
    <Component.Nav state={state##nav} actions={actions##nav} />
    <Component.BookList state={state##bookList} actions={actions##bookList} />
  </div>;

Js.Nullable.bind(Hyperapp.getElementById("main"), (. main) =>
  Hyperapp.app(~state, ~actions, ~view, main)
);
