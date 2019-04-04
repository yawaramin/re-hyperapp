type tab = All | Now | Soon;
type state = {. tab};
type actions = {. setTab: (. tab) => Js.t(state)};
type props = unit;

let str = Yawaramin_ReHyperapp.string;

module Tab = {
  let isActive(stateTab, tab) = if (stateTab == tab) "is-active" else "";

  let make(~currTab, ~code, ~label, ~setTab, _) =
    <a _class=isActive(currTab, code) onclick={(. _event) => setTab(. code)}>
      {str(label)}
    </a>;
};

let state = {"tab": All};
let actions = {"setTab": (. tab) => {"tab": tab}};

let make(~state, ~actions, ~props=(), _) = {
  ignore(props);
  let setTab = actions##setTab;

  <nav _class="panel">
    <p _class="panel-heading">{str("Library")}</p>
    <div _class="panel-block">
      <p _class="control has-icons-left">
        <input _class="input is-small" _type="text" placeholder="Filter" />
      </p>
    </div>
    <p _class="panel-tabs">
      <Tab currTab=state##tab code=All label="All" setTab />
      <Tab currTab=state##tab code=Now label="Available Now" setTab />
      <Tab currTab=state##tab code=Soon label="Available Soon" setTab />
    </p>
  </nav>
};
