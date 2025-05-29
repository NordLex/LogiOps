polkit.addRule(function(action, subject) {
    if (action.id == "dev.nordlex.logiops.manage-service") {
        if (subject.isInGroup("wheel") || subject.isInGroup("sudo")) {
            return polkit.Result.YES;
        }
        return polkit.Result.AUTH_ADMIN;
    }
});