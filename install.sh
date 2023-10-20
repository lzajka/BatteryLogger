
systemctl --user daemon-reload

systemctl --user enable battery-logger.timer
systemctl --user enable battery-logger.service
systemctl --user start battery-logger.timer