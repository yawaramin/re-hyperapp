type vdom;
type element;

external string: string => vdom = "%identity";
external int: int => vdom = "%identity";

[@bs.module "hyperapp"]
external h: (string, ~attrs: Js.t({..})=?, array(vdom)) => vdom = "";

[@bs.module "hyperapp"]
external app: (
  ~state: Js.t({..}) as 'state,
  ~actions: Js.t({..}) as 'actions,
  ~view: [@bs] ('state, 'actions) => vdom,
  element) =>
  unit =
  "";

[@bs.return nullable] [@bs.scope "document"] [@bs.val]
external getElementById: string => option(element) = "";

type state = {. "count": int};

let state = {"count": 0};

let actions = {
  "down": [@bs] value => [@bs] (state: state) => {"count": state##count - value},
  "up": [@bs] value => [@bs] (state: state) => {"count": state##count + value},
  "reset": [@bs] () => state,
  "set": [@bs] count => {"count": count}
};

let view = [@bs] (state, actions) => h("div", [|
  h("h1", [|int(state##count)|]),

  h("button",
    ~attrs={"onclick": (_) =>
      { let action = actions##down; [@bs] action(1) }},
    [|string("-")|]),

  h("button",
    ~attrs={"onclick": (_) =>
      { let action = actions##up; [@bs] action(1) }},
    [|string("+")|]),

  h("button",
    ~attrs={"onclick": (_) => { let action = actions##reset; [@bs] action() }},
    [|string("Reset")|]),

  h("button",
    ~attrs={"onclick": (_) => { let action = actions##set; [@bs] action(100) }},
    [|string("Set to 100")|])
|]);

switch (getElementById("main")) {
| Some(main) => app(~state, ~actions, ~view, main)
| None => ()
};
