/** Sample app to show how to idiomatically structure a ReHyperapp
    project. It's mostly the same as a normal Hyperapp project, just with
    more types. */

module Component = Demo_Component;
module Hy = Yawaramin_ReHyperapp;

let state = {"main": Component.Main.state};
let actions = {"main": Component.Main.actions};
let view(. state, actions) =
  <Component.Main state={state##main} actions={actions##main} />;
let _ = "main" |> Hy.getElementById |> Hy.make(~state, ~actions, ~view);
