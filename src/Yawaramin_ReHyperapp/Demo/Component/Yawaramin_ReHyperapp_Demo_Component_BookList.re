module Hyperapp = Yawaramin_ReHyperapp;

type book = {.
  "id": int,
  "copies": int,
  "title": string,
  "author": string,
  "description": string,
};

type state = {. "value": option(array(book))};
type actions = {. "set": (. array(book)) => state};
type props = unit;

let state = {"value": None};
let actions = {"set": (. books: array(book)) => {"value": Some(books)}};
let make(~state, ~actions, ~props=(), _children) = <span></span>;
