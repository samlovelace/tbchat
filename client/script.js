document.addEventListener("DOMContentLoaded", function() {
    const welcomePrompt = document.getElementById("welcome-prompt");
    const chatContent = document.getElementById("chat-content");
    const joinButton = document.getElementById("join-button");
    const usernameInput = document.getElementById("username");
    const roomSelect = document.getElementById("room-select");
    const roomTitle = document.getElementById("room-title");
    const themeSelect = document.getElementById("theme-select");
    const themeStylesheet = document.getElementById("theme-stylesheet");

    // Connect to WebSocket server
    const socket = new WebSocket("ws://localhost:9002");  // Update to your server address

    // Event listener for theme change
    themeSelect.addEventListener("change", (event) => {
        themeStylesheet.href = event.target.value;
    });

    socket.onopen = function() {
        // Request the list of active rooms
        const roomRequest = JSON.stringify({ action: "get_rooms" });
        socket.send(roomRequest);
    };

    function getCurrentTimestamp() {
        const now = new Date();
        return now.toTimeString().split(' ')[0];  // HH:MM:SS format
    }

    // Define a Solarized-inspired color palette
    const colorPalette = [
        "#268BD2", "#B58900", "#CB4B16", "#6C71C4",
        "#D33682", "#859900", "#DC322F", "#93A1A1", "#073642"
    ];
    
    // Map to store colors for each unique user
    const userColors = {};

    // Function to assign or retrieve a color for a username
    function getColorForUsername(username) {
        if (!userColors[username]) {
            // Assign a color from the palette based on the current size of the map
            const color = colorPalette[Object.keys(userColors).length % colorPalette.length];
            userColors[username] = color;
        }
        return userColors[username];
    }

    socket.onmessage = function(event) {
        const data = JSON.parse(event.data);

        // Populate rooms dropdown when the room list is received
        if (data.action === "room_list") {
            roomSelect.innerHTML = ""; // Clear existing options
            data.rooms.forEach(room => {
                const option = document.createElement("option");
                option.value = room;
                option.textContent = room;
                roomSelect.appendChild(option);
            });
        } else if (data.action === "message") {
            const chatLog = document.getElementById("chat-log");
            const messageElement = document.createElement("div");
            messageElement.classList.add("message");
    
            // Create a span for the username
            const usernameSpan = document.createElement("span");
            usernameSpan.classList.add("username");
            usernameSpan.textContent = `${data.username}: `;
            usernameSpan.style.color = getColorForUsername(data.username);
    
            // Create a span for the message text
            const messageTextSpan = document.createElement("span");
            messageTextSpan.classList.add("message-text");
            messageTextSpan.textContent = data.message;
            messageTextSpan.style.color = usernameSpan.style.color;

            // Create a span for the timestamp, aligned to the right
            const timestampSpan = document.createElement("span");
            timestampSpan.classList.add("timestamp");
            timestampSpan.textContent = data.timestamp;
    
            // Append both spans to the message element
            messageElement.appendChild(usernameSpan);
            messageElement.appendChild(messageTextSpan);
            messageElement.appendChild(timestampSpan);
    
            // Append the message element to the chat log
            chatLog.appendChild(messageElement);
            chatLog.scrollTop = chatLog.scrollHeight; // Auto-scroll to latest message
        }
    };

    joinButton.addEventListener("click", function() {
        const username = usernameInput.value.trim();
        const room = roomSelect.value;

        // Validate username and room selection
        if (!username) {
            alert("Please enter a username.");
            return;
        }
        if (!room) {
            alert("Please select a room to join.");
            return;
        }

        // Initialize chat
        initializeChat(username, room);
    });

    function initializeChat(username, room) {
        // Hide welcome prompt
        welcomePrompt.style.display = "none";
        // Show main chat content
        chatContent.style.display = "block";
        // Set room title
        roomTitle.textContent = `@${room}`;

        // Send join message to the server
        const joinMessage = JSON.stringify({
            action: "join",
            room: room,
            username: username
        });
        socket.send(joinMessage);

        // Handle sending messages
        const sendButton = document.getElementById("send");
        const messageInput = document.getElementById("message");

        // Send a message with a timestamp
        function sendMessage() {
            const messageText = messageInput.value.trim();
                if (messageText) {
                    const messageData = JSON.stringify({
                    action: "message",
                    room: room,
                    username: username,
                    message: messageText,
                    timestamp: getCurrentTimestamp()  // Add timestamp here
                });
            socket.send(messageData);
            messageInput.value = ""; // Clear the input field
        }
}

        // Event listener for the Send button and Ctrl+Enter shortcut
        sendButton.addEventListener("click", sendMessage);
        messageInput.addEventListener("keydown", function(event) {
            if (event.ctrlKey && event.key === "Enter") {
                sendMessage();
            }
        });
    }
});

