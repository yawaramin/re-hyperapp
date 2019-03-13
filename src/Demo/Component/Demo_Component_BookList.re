module Hyperapp = Yawaramin_ReHyperapp;

type book = {.
  "id": int,
  "copies": int,
  "title": string,
  "author": string,
  "description": string,
};

/* There is some potential for confusion here, because we need to define
   the [state] and [action] types as normal {i OCaml object} types, not
   BuckleScript object ([Js.t(something)]) types; but at the same time we
   need to create their initial values as BuckleScript objects.

   This is because Hyperapp needs the actual state and actions objects to
   be JavaScript objects, so I enforced that in the module type. */

type state = {. value: option(array(book))};

/* Note how the [state] type needs to be wrapped in [Js.t] because
   actions actually need to return JavaScript objects containing the new
   state. */
type actions = {. set: (. array(book)) => Js.t(state)};

type props = unit;

let state = {"value": None};
let actions = {"set": (. books: array(book)) => {"value": Some(books)}};
let make(~state, ~actions, ~props=(), _children) = <span></span>;
