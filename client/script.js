document.addEventListener("DOMContentLoaded", function() {
    const welcomePrompt = document.getElementById("welcome-prompt");
    const chatContent = document.getElementById("chat-content");
    const joinButton = document.getElementById("join-button");
    const usernameInput = document.getElementById("username");
    const roomSelect = document.getElementById("room-select");
    const roomTitle = document.getElementById("room-title");

    // Connect to WebSocket server
    const socket = new WebSocket("ws://localhost:9002");  // Update to your server address

    socket.onopen = function() {
        // Request the list of active rooms
        const roomRequest = JSON.stringify({ action: "get_rooms" });
        socket.send(roomRequest);
    };

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
    
            // Create a span for the message text
            const messageTextSpan = document.createElement("span");
            messageTextSpan.classList.add("message-text");
            messageTextSpan.textContent = data.message;
    
            // Append both spans to the message element
            messageElement.appendChild(usernameSpan);
            messageElement.appendChild(messageTextSpan);
    
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

        function sendMessage() {
            const message = messageInput.value.trim();
            if (message) {
                const messageData = JSON.stringify({
                    action: "message",
                    room: room,
                    username: username,
                    message: message
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

