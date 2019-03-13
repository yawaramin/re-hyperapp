/** (WIP) very minimalistic bindings to
    {{:https://github.com/jorgebucaran/hyperapp}Hyperapp}. Hyperapp has a
    very tiny API surface and already has a well-defined architecture, so
    we just follow that.

    JSX support is implemented in the [ReactDOMRe] and [ReasonReact]
    modules. See the former for more details. Note that both of these
    modules {i should not} be used directly; their purpose is to provide
    JSX support. */

/** Virtual DOM elements. I.e. the things that get rendered by views. */
type vdom;

/** Suggested type of a custom component (i.e. a capitalized JSX
    element). This module type makes it possible to create higher-order
    components using OCaml functors, by declaring the functors to accept
    and return this type as input and output.

    Strictly speaking, this exact type is not needed to support custom
    elements in JSX; at a minimum, the JSX transform just needs the last
    parameter ([children]), but usually you'll want to pass in some
    states, props, and actions.

    See also [ReasonReact] for more details on capitalized components,
    and [Yawaramin_ReHyperapp_Demo_Component_BookList.rei] for an example
    of how to enforce this module type on any given component. */
module type Component = {
  type state;
  type actions;
  type props;

  /* Note that you'll need to define the [state] and [actions] types as
     OCaml object types, but instantiate the below two values as
     BuckleScript objects. See
     [Yawaramin_ReHyperapp_Demo_Component_BookList.re] for more details. */

  let state: Js.t(state);
  let actions: Js.t(actions);

  let make: (
    ~state: Js.t(state),
    ~actions: Js.t(actions),
    ~props: props=?,
    array(vdom),
  ) => vdom;
};

type element = Dom.element;

/** A Hyperapp instance that can be mounted on the page. */
type t;

// Helpers to inject basic values into vdom/JSX.

external string: string => vdom = "%identity";
external int: int => vdom = "%identity";
external float: float => vdom = "%identity";

// The following two helpers are mostly not needed thanks to JSX support.

/** [h(tagName, attrs, children)] creates a [vdom] element with tag name
    [tagName], attributes [attrs], and child elements [children]. This is
    mostly useful for creating attributes that JSX doesn't support, e.g.
    [<div data-foo="bar">]. */
[@bs.module "hyperapp"]
external h: (string, Js.t({..}), array(vdom)) => vdom = "";

/** [h_(tagName, children)] creates a [vdom] element like above but with
    no attributes. */
[@bs.module "hyperapp"]
external h_: (string, [@bs.as {json|{}|json}] _, array(vdom)) => vdom = "h";

/** [make(~state, ~actions, ~view, element)] creates a Hyperapp instance.
    This is the main entry point to using this binding. Most of the type
    safety of the overall app comes from the way this function is typed:
    the view function must work with the state (model) and actions. */
[@bs.module "hyperapp"] external make: (
  ~state: Js.t({..}) as 'state,
  ~actions: Js.t({..}) as 'actions,
  ~view: (. 'state, 'actions) => vdom,
  Js.nullable(element),
) => t = "app";

/** Helper to get the DOM element that the [app] function needs to mount
    the app onto the page. */
[@bs.scope "document"] [@bs.val]
external getElementById: string => Js.nullable(element) = "";
