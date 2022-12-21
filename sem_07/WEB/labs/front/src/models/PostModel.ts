import UserModel from "./UserModel";

class PreviewModel {
    constructor(
        public id: number = -1, 
        public name: string = "",
        public author: UserModel = new UserModel(),
        public information: string = "", 
        public city: string = "", 
        public date: string = ""
        ) {
            this.id = id
            this.name = name
            this.author = author
            this.information = information
            this.city = city
            this.date = date
    }
}

export default PreviewModel