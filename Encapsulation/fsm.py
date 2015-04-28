class fsm:
    def __init__(self):
        self.transitions = {}
        self.states = []
        self.events = []
        self.curState = None
        self.curEvent = None
        self.prevState =None

    def add_transition(self, state1, state2, event, funct):
        key = state1+'.'+event
        self.transitions [key] = (state2, funct)

    def add_state(self, state):
        self.states.append(state)

    def add_event(self, event):
        self.events.append(event)

    def set_state(self, state):
        self.curState = state

    def set_event(self, event):
        self.curEvent = event

    def run(self):
        event = self.curEvent
        state = self.curState
        key = state+'.'+event
        self.prevState = state
        self.curState = self.transitions [key][0]
        st = "Transition - Old State : "+state+"; Event : "+event+"; New state : "+self.curState
        st = st+"; Action : "+self.transitions [key][1].__name__+"()"
        print st
        return self.transitions [key][1]
