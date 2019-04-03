let str = Yawaramin_ReHyperapp.string;

module Tab = {
  let isActive(stateTab, tab) = if (stateTab === tab) "is-active" else "";

  let make(~currTab, ~code, ~label, ~setTab, _) =
    <a _class=isActive(currTab, code) onclick={(. _event) => setTab(. code)} >
      {str(label)}
    </a>;
};

let state = {"tab": `all};
let actions = {"setTab": (. tab: [`all | `now | `soon]) => {"tab": tab}};

let make(~state, ~actions, _) = {
  let setTab = actions##setTab;

  <nav _class="panel">
    <p _class="panel-heading">{str("Library")}</p>
    <div _class="panel-block">
      <p _class="control has-icons-left">
        <input _class="input is-small" _type="text" placeholder="search" />
      </p>
    </div>
    <p _class="panel-tabs">
      <Tab currTab=state##tab code=`all label="All" setTab />
      <Tab currTab=state##tab code=`now label="Available Now" setTab />
      <Tab currTab=state##tab code=`soon label="Available Soon" setTab />
    </p>
  </nav>
};
