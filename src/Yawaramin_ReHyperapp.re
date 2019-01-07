/** (WIP) very minimalistic bindings to
    {{:https://github.com/jorgebucaran/hyperapp}Hyperapp}. Hyperapp has a
    very tiny API surface and already has a well-defined architecture, so
    we just follow that.

    JSX support is implemented in the [ReactDOMRe] module. */

type vdom;
type app;
type element;

external string: string => vdom = "%identity";
external int: int => vdom = "%identity";
external float: float => vdom = "%identity";

[@bs.module "hyperapp"]
external h: (string, Js.t({..}), array(vdom)) => vdom = "";

[@bs.module "hyperapp"]
external h_: (string, [@bs.as {json|{}|json}] _, array(vdom)) => vdom = "h";

/** Most of the type safety of the overall app comes from the way this
    function is typed: the view function must work with the state (model)
    and actions. */
[@bs.module "hyperapp"] external app: (
  ~state: Js.t({..}) as 'state,
  ~actions: Js.t({..}) as 'actions,
  ~view: (. 'state, 'actions) => vdom,
  element,
) => app =
  "";

/** Helper to get the DOM element that the [app] function needs to mount
    the app onto the page. */
[@bs.scope "document"] [@bs.val]
external getElementById: string => Js.nullable(element) = "";
