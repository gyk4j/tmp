let evtSource = null

function start(){
    if(evtSource == null){
        evtSource = new EventSource("/events?stream=messages");

        // Listening for message events
        evtSource.onmessage = (event) => {
            const newElement = document.createElement("li");
            const eventList = document.getElementById("list");
        
            newElement.textContent = `message: ${event.data}`;
            eventList.appendChild(newElement);
        };

        // Listening for custom events
        evtSource.addEventListener("ping", (event) => {
            const newElement = document.createElement("li");
            const eventList = document.getElementById("list");
            console.log(event.data);
            const time = JSON.parse(event.data).time;
            newElement.textContent = `ping at ${time}`;
            eventList.appendChild(newElement);
        });

        // Error handling
        evtSource.onerror = (err) => {
            console.error("EventSource failed:", err);
        };
    }
}

function stop(){
    if(evtSource != null){
        // Closing event streams
        evtSource.close();

        evtSource = null;
    }
}

