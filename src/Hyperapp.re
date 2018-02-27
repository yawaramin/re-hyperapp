type vdom;
type app;
type element;

external string: string => vdom = "%identity";
external int: int => vdom = "%identity";

[@bs.module "hyperapp"]
external h: (string, Js.t({..}), array(vdom)) => vdom = "";

let empty = Js.Obj.empty();
let h_(tagName, children) = h(tagName, empty, children);

[@bs.module "hyperapp"] external app: (
  ~state: Js.t({..}) as 'state,
  ~actions: Js.t({..}) as 'actions,
  ~view: [@bs] ('state, 'actions) => vdom,
  element) =>
  app =
  "";

[@bs.scope "document"] [@bs.val]
external getElementById: string => Js.nullable(element) = "";
