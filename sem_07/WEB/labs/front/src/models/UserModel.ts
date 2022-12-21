class UserModel {
    constructor(
        public id: number = -1, 
        public full_name: string = "",
        public login: string = "", 
        public city: string = "",
        public access: string = ""
        ) {
            this.id = id
            this.full_name = full_name
            this.login = login
            this.city = city
            this.access = access
    }
}

export default UserModel