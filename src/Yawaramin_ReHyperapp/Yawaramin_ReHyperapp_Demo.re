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

let view = (. state, actions) => Hyperapp.h_("div", [|
  Component.Nav.view(. state##nav, actions##nav),
  Component.BookList.view(. state##bookList, actions##bookList),
|]);

Js.Nullable.bind(Hyperapp.getElementById("main"), (. main) =>
  Hyperapp.app(~state, ~actions, ~view, main)
);
